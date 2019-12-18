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
struct scx200_acb_iface {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct scx200_acb_iface* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  scx200_cleanup_iface (struct scx200_acb_iface*) ; 

__attribute__((used)) static int scx200_remove(struct platform_device *pdev)
{
	struct scx200_acb_iface *iface;

	iface = platform_get_drvdata(pdev);
	scx200_cleanup_iface(iface);

	return 0;
}