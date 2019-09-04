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
struct omap_aes_dev {int flags; } ;

/* Variables and functions */
 int FLAGS_ASSOC_DATA_ST_SHIFT ; 
 int FLAGS_IN_DATA_ST_SHIFT ; 
 int FLAGS_OUT_DATA_ST_SHIFT ; 
 int OMAP_CRYPTO_COPY_MASK ; 

void omap_aes_clear_copy_flags(struct omap_aes_dev *dd)
{
	dd->flags &= ~(OMAP_CRYPTO_COPY_MASK << FLAGS_IN_DATA_ST_SHIFT);
	dd->flags &= ~(OMAP_CRYPTO_COPY_MASK << FLAGS_OUT_DATA_ST_SHIFT);
	dd->flags &= ~(OMAP_CRYPTO_COPY_MASK << FLAGS_ASSOC_DATA_ST_SHIFT);
}