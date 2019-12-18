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
typedef  int /*<<< orphan*/  avmcard ;

/* Variables and functions */
 int ReadReg (int /*<<< orphan*/ *,int) ; 
 scalar_t__ WriteReg (int /*<<< orphan*/ *,int,int) ; 
 int b1dma_detect (int /*<<< orphan*/ *) ; 

int b1pciv4_detect(avmcard *card)
{
	int ret, i;

	if ((ret = b1dma_detect(card)) != 0)
		return ret;

	for (i = 0; i < 5; i++) {
		if (WriteReg(card, 0x80A00000, 0x21) != 0)
			return 6;
		if ((ReadReg(card, 0x80A00000) & 0x01) != 0x01)
			return 7;
	}
	for (i = 0; i < 5; i++) {
		if (WriteReg(card, 0x80A00000, 0x20) != 0)
			return 8;
		if ((ReadReg(card, 0x80A00000) & 0x01) != 0x00)
			return 9;
	}

	return 0;
}