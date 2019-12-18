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
struct usdhi6_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USDHI6_SD_INFO1_CARD_CD ; 
 int /*<<< orphan*/  usdhi6_irq_enable (struct usdhi6_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usdhi6_only_cd(struct usdhi6_host *host)
{
	/* Mask all except card hotplug */
	usdhi6_irq_enable(host, USDHI6_SD_INFO1_CARD_CD, 0);
}