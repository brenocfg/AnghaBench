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
typedef  scalar_t__ u16 ;
struct vadc_priv {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vadc_write(struct vadc_priv *vadc, u16 offset, u8 data)
{
	return regmap_write(vadc->regmap, vadc->base + offset, data);
}