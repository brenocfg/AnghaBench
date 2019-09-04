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
struct omap_aes_dev {int flags; int assoc_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_REG_A_LEN ; 
 int /*<<< orphan*/  AES_REG_LENGTH_N (int) ; 
 int FLAGS_GCM ; 
 int /*<<< orphan*/  omap_aes_dma_trigger_omap2 (struct omap_aes_dev*,int) ; 
 int /*<<< orphan*/  omap_aes_write (struct omap_aes_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap_aes_dma_trigger_omap4(struct omap_aes_dev *dd, int length)
{
	omap_aes_write(dd, AES_REG_LENGTH_N(0), length);
	omap_aes_write(dd, AES_REG_LENGTH_N(1), 0);
	if (dd->flags & FLAGS_GCM)
		omap_aes_write(dd, AES_REG_A_LEN, dd->assoc_len);

	omap_aes_dma_trigger_omap2(dd, length);
}