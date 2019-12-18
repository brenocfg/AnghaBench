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
typedef  int /*<<< orphan*/  u8 ;
struct trf7970a {int /*<<< orphan*/  md_rf_tech; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct trf7970a* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 

__attribute__((used)) static int trf7970a_tg_get_rf_tech(struct nfc_digital_dev *ddev, u8 *rf_tech)
{
	struct trf7970a *trf = nfc_digital_get_drvdata(ddev);

	dev_dbg(trf->dev, "Get RF Tech - state: %d, rf_tech: %d\n",
		trf->state, trf->md_rf_tech);

	*rf_tech = trf->md_rf_tech;

	return 0;
}