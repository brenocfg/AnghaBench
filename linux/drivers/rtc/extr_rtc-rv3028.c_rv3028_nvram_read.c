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

/* Variables and functions */
 scalar_t__ RV3028_RAM1 ; 
 int regmap_bulk_read (void*,scalar_t__,void*,size_t) ; 

__attribute__((used)) static int rv3028_nvram_read(void *priv, unsigned int offset, void *val,
			     size_t bytes)
{
	return regmap_bulk_read(priv, RV3028_RAM1 + offset, val, bytes);
}