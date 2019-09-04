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
struct cx88_audio_dev {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx88_core_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct cx88_audio_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cx88_free(struct cx88_audio_dev *chip)
{
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

	cx88_core_put(chip->core, chip->pci);

	pci_disable_device(chip->pci);
	return 0;
}