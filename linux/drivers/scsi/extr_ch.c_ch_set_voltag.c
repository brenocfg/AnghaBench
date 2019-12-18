#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_7__ {TYPE_1__* device; } ;
typedef  TYPE_2__ scsi_changer ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {int lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DPRINTK (char*,char*,char*,int,int*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SEND_VOLUME_TAG ; 
 int /*<<< orphan*/  ch_check_voltag (int*) ; 
 int ch_do_scsi (TYPE_2__*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int ch_elem_to_typecode (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ch_set_voltag(scsi_changer *ch, u_int elem,
	      int alternate, int clear, u_char *tag)
{
	u_char  cmd[12];
	u_char  *buffer;
	int result;

	buffer = kzalloc(512, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	DPRINTK("%s %s voltag: 0x%x => \"%s\"\n",
		clear     ? "clear"     : "set",
		alternate ? "alternate" : "primary",
		elem, tag);
	memset(cmd,0,sizeof(cmd));
	cmd[0]  = SEND_VOLUME_TAG;
	cmd[1] = ((ch->device->lun & 0x7) << 5) |
		ch_elem_to_typecode(ch,elem);
	cmd[2] = (elem >> 8) & 0xff;
	cmd[3] = elem        & 0xff;
	cmd[5] = clear
		? (alternate ? 0x0d : 0x0c)
		: (alternate ? 0x0b : 0x0a);

	cmd[9] = 255;

	memcpy(buffer,tag,32);
	ch_check_voltag(buffer);

	result = ch_do_scsi(ch, cmd, 12, buffer, 256, DMA_TO_DEVICE);
	kfree(buffer);
	return result;
}