#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct packet_command {char* buffer; int buflen; } ;
struct mode_page_header {int /*<<< orphan*/  mode_data_length; int /*<<< orphan*/  desc_length; } ;
struct cdrom_device_info {int /*<<< orphan*/  name; int /*<<< orphan*/  mrw_mode_page; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_READ ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int cdrom_mode_select (struct cdrom_device_info*,struct packet_command*) ; 
 int cdrom_mode_sense (struct cdrom_device_info*,struct packet_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mrw_address_space ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdrom_mrw_set_lba_space(struct cdrom_device_info *cdi, int space)
{
	struct packet_command cgc;
	struct mode_page_header *mph;
	char buffer[16];
	int ret, offset, size;

	init_cdrom_command(&cgc, buffer, sizeof(buffer), CGC_DATA_READ);

	cgc.buffer = buffer;
	cgc.buflen = sizeof(buffer);

	ret = cdrom_mode_sense(cdi, &cgc, cdi->mrw_mode_page, 0);
	if (ret)
		return ret;

	mph = (struct mode_page_header *)buffer;
	offset = be16_to_cpu(mph->desc_length);
	size = be16_to_cpu(mph->mode_data_length) + 2;

	buffer[offset + 3] = space;
	cgc.buflen = size;

	ret = cdrom_mode_select(cdi, &cgc);
	if (ret)
		return ret;

	pr_info("%s: mrw address space %s selected\n",
		cdi->name, mrw_address_space[space]);
	return 0;
}