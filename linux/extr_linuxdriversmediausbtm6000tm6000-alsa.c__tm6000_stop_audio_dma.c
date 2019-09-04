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
struct tm6000_core {int dummy; } ;
struct snd_tm6000_card {struct tm6000_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  TM6010_REQ07_RCC_ACTIVE_IF ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  tm6000_set_reg_mask (struct tm6000_core*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int _tm6000_stop_audio_dma(struct snd_tm6000_card *chip)
{
	struct tm6000_core *core = chip->core;

	dprintk(1, "Stopping audio DMA\n");

	/* Disables audio */
	tm6000_set_reg_mask(core, TM6010_REQ07_RCC_ACTIVE_IF, 0x00, 0x40);

	return 0;
}