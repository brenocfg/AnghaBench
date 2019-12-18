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
struct pci_esp_priv {int dummy; } ;
struct esp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct pci_esp_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct pci_esp_priv *pci_esp_get_priv(struct esp *esp)
{
	return dev_get_drvdata(esp->dev);
}