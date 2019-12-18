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
struct vadc_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VADC_EN_CTL1 ; 
 int /*<<< orphan*/  VADC_EN_CTL1_SET ; 
 int vadc_write (struct vadc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vadc_set_state(struct vadc_priv *vadc, bool state)
{
	return vadc_write(vadc, VADC_EN_CTL1, state ? VADC_EN_CTL1_SET : 0);
}