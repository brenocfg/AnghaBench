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
typedef  int /*<<< orphan*/  u32 ;
struct omap_sham_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_sham_read (struct omap_sham_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_sham_write (struct omap_sham_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void omap_sham_write_mask(struct omap_sham_dev *dd, u32 address,
					u32 value, u32 mask)
{
	u32 val;

	val = omap_sham_read(dd, address);
	val &= ~mask;
	val |= value;
	omap_sham_write(dd, address, val);
}