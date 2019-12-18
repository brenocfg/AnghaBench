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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  RV8803_RAM ; 
 int rv8803_write_reg (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rv8803_nvram_write(void *priv, unsigned int offset, void *val,
			      size_t bytes)
{
	int ret;

	ret = rv8803_write_reg(priv, RV8803_RAM, *(u8 *)val);
	if (ret)
		return ret;

	return 0;
}