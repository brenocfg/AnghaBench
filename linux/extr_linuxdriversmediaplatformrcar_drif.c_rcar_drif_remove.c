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
struct rcar_drif_sdr {int dummy; } ;
struct rcar_drif {scalar_t__ num; struct rcar_drif_sdr* sdr; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct rcar_drif* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rcar_drif_sdr_remove (struct rcar_drif_sdr*) ; 

__attribute__((used)) static int rcar_drif_remove(struct platform_device *pdev)
{
	struct rcar_drif *ch = platform_get_drvdata(pdev);
	struct rcar_drif_sdr *sdr = ch->sdr;

	/* Channel 0 will be the SDR instance */
	if (ch->num)
		return 0;

	/* SDR instance */
	rcar_drif_sdr_remove(sdr);

	return 0;
}