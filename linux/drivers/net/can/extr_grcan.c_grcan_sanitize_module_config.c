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

/* Variables and functions */
 int /*<<< orphan*/  grcan_sanitize_enable0 (struct platform_device*) ; 
 int /*<<< orphan*/  grcan_sanitize_enable1 (struct platform_device*) ; 
 int /*<<< orphan*/  grcan_sanitize_rxsize (struct platform_device*) ; 
 int /*<<< orphan*/  grcan_sanitize_select (struct platform_device*) ; 
 int /*<<< orphan*/  grcan_sanitize_txsize (struct platform_device*) ; 

__attribute__((used)) static void grcan_sanitize_module_config(struct platform_device *ofdev)
{
	grcan_sanitize_enable0(ofdev);
	grcan_sanitize_enable1(ofdev);
	grcan_sanitize_select(ofdev);
	grcan_sanitize_txsize(ofdev);
	grcan_sanitize_rxsize(ofdev);
}