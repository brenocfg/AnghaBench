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
struct spi_device {int dummy; } ;
struct mrf24j40 {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee802154_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printdev (struct mrf24j40*) ; 
 struct mrf24j40* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int mrf24j40_remove(struct spi_device *spi)
{
	struct mrf24j40 *devrec = spi_get_drvdata(spi);

	dev_dbg(printdev(devrec), "remove\n");

	ieee802154_unregister_hw(devrec->hw);
	ieee802154_free_hw(devrec->hw);
	/* TODO: Will ieee802154_free_device() wait until ->xmit() is
	 * complete? */

	return 0;
}