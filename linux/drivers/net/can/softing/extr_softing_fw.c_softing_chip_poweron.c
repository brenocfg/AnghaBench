#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void** chip; void* license; void* hw_version; void* fw_version; int /*<<< orphan*/  serial; } ;
struct softing {int /*<<< orphan*/ * dpram; TYPE_1__ id; } ;

/* Variables and functions */
 size_t DPRAM_FCT_PARAM ; 
 int _softing_fct_cmd (struct softing*,int,int,char*) ; 
 void* ioread16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int softing_fct_cmd (struct softing*,int,char*) ; 
 int softing_reset_chip (struct softing*) ; 

int softing_chip_poweron(struct softing *card)
{
	int ret;
	/* sync */
	ret = _softing_fct_cmd(card, 99, 0x55, "sync-a");
	if (ret < 0)
		goto failed;

	ret = _softing_fct_cmd(card, 99, 0xaa, "sync-b");
	if (ret < 0)
		goto failed;

	ret = softing_reset_chip(card);
	if (ret < 0)
		goto failed;
	/* get_serial */
	ret = softing_fct_cmd(card, 43, "get_serial_number");
	if (ret < 0)
		goto failed;
	card->id.serial = ioread32(&card->dpram[DPRAM_FCT_PARAM]);
	/* get_version */
	ret = softing_fct_cmd(card, 12, "get_version");
	if (ret < 0)
		goto failed;
	card->id.fw_version = ioread16(&card->dpram[DPRAM_FCT_PARAM + 2]);
	card->id.hw_version = ioread16(&card->dpram[DPRAM_FCT_PARAM + 4]);
	card->id.license = ioread16(&card->dpram[DPRAM_FCT_PARAM + 6]);
	card->id.chip[0] = ioread16(&card->dpram[DPRAM_FCT_PARAM + 8]);
	card->id.chip[1] = ioread16(&card->dpram[DPRAM_FCT_PARAM + 10]);
	return 0;
failed:
	return ret;
}