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
struct pnp_dev {int dummy; } ;
struct ene_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ene_enable_wake (struct ene_device*,int) ; 
 struct ene_device* pnp_get_drvdata (struct pnp_dev*) ; 

__attribute__((used)) static void ene_shutdown(struct pnp_dev *pnp_dev)
{
	struct ene_device *dev = pnp_get_drvdata(pnp_dev);
	ene_enable_wake(dev, true);
}