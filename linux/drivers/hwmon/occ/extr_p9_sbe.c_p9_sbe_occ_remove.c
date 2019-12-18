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
struct platform_device {int dummy; } ;
struct p9_sbe_occ {int /*<<< orphan*/ * sbe; } ;
struct occ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  occ_shutdown (struct occ*) ; 
 struct occ* platform_get_drvdata (struct platform_device*) ; 
 struct p9_sbe_occ* to_p9_sbe_occ (struct occ*) ; 

__attribute__((used)) static int p9_sbe_occ_remove(struct platform_device *pdev)
{
	struct occ *occ = platform_get_drvdata(pdev);
	struct p9_sbe_occ *ctx = to_p9_sbe_occ(occ);

	ctx->sbe = NULL;
	occ_shutdown(occ);

	return 0;
}