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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdhci_set_card_detection (struct sdhci_host*,int) ; 

__attribute__((used)) static void sdhci_enable_card_detection(struct sdhci_host *host)
{
	sdhci_set_card_detection(host, true);
}