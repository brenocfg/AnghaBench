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

/* Variables and functions */
 int /*<<< orphan*/  fmr2_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_set_drvdata (struct pnp_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fmr2_pnp_remove(struct pnp_dev *pdev)
{
	fmr2_remove(pnp_get_drvdata(pdev));
	pnp_set_drvdata(pdev, NULL);
}