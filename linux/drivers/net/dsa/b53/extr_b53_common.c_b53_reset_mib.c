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
typedef  int u8 ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_GLOBAL_CONFIG ; 
 int /*<<< orphan*/  B53_MGMT_PAGE ; 
 int GC_RESET_MIB ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void b53_reset_mib(struct b53_device *priv)
{
	u8 gc;

	b53_read8(priv, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, &gc);

	b53_write8(priv, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, gc | GC_RESET_MIB);
	msleep(1);
	b53_write8(priv, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, gc & ~GC_RESET_MIB);
	msleep(1);
}