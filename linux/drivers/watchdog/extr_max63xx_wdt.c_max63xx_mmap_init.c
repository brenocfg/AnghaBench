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
struct max63xx_wdt {int /*<<< orphan*/  set; int /*<<< orphan*/  ping; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max63xx_mmap_ping ; 
 int /*<<< orphan*/  max63xx_mmap_set ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max63xx_mmap_init(struct platform_device *p, struct max63xx_wdt *wdt)
{
	wdt->base = devm_platform_ioremap_resource(p, 0);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	spin_lock_init(&wdt->lock);

	wdt->ping = max63xx_mmap_ping;
	wdt->set = max63xx_mmap_set;
	return 0;
}