#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mii_bus {int /*<<< orphan*/  dev; TYPE_1__* parent; scalar_t__ priv; } ;
struct hns_mdio_sc_reg {int /*<<< orphan*/  mdio_clk_st; int /*<<< orphan*/  mdio_clk_en; int /*<<< orphan*/  mdio_reset_st; int /*<<< orphan*/  mdio_reset_dreq; int /*<<< orphan*/  mdio_clk_dis; int /*<<< orphan*/  mdio_reset_req; } ;
struct hns_mdio_device {struct hns_mdio_sc_reg sc_reg; int /*<<< orphan*/  subctrl_vbase; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_3__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (TYPE_1__*) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  MDIO_CHECK_CLR_ST ; 
 int /*<<< orphan*/  MDIO_CHECK_SET_ST ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ dev_of_node (TYPE_1__*) ; 
 scalar_t__ is_acpi_node (int /*<<< orphan*/ ) ; 
 int mdio_sc_cfg_reg_write (struct hns_mdio_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_mdio_reset(struct mii_bus *bus)
{
	struct hns_mdio_device *mdio_dev = (struct hns_mdio_device *)bus->priv;
	const struct hns_mdio_sc_reg *sc_reg;
	int ret;

	if (dev_of_node(bus->parent)) {
		if (!mdio_dev->subctrl_vbase) {
			dev_err(&bus->dev, "mdio sys ctl reg has not maped\n");
			return -ENODEV;
		}

		sc_reg = &mdio_dev->sc_reg;
		/* 1. reset req, and read reset st check */
		ret = mdio_sc_cfg_reg_write(mdio_dev, sc_reg->mdio_reset_req,
					    0x1, sc_reg->mdio_reset_st, 0x1,
					    MDIO_CHECK_SET_ST);
		if (ret) {
			dev_err(&bus->dev, "MDIO reset fail\n");
			return ret;
		}

		/* 2. dis clk, and read clk st check */
		ret = mdio_sc_cfg_reg_write(mdio_dev, sc_reg->mdio_clk_dis,
					    0x1, sc_reg->mdio_clk_st, 0x1,
					    MDIO_CHECK_CLR_ST);
		if (ret) {
			dev_err(&bus->dev, "MDIO dis clk fail\n");
			return ret;
		}

		/* 3. reset dreq, and read reset st check */
		ret = mdio_sc_cfg_reg_write(mdio_dev, sc_reg->mdio_reset_dreq,
					    0x1, sc_reg->mdio_reset_st, 0x1,
					    MDIO_CHECK_CLR_ST);
		if (ret) {
			dev_err(&bus->dev, "MDIO dis clk fail\n");
			return ret;
		}

		/* 4. en clk, and read clk st check */
		ret = mdio_sc_cfg_reg_write(mdio_dev, sc_reg->mdio_clk_en,
					    0x1, sc_reg->mdio_clk_st, 0x1,
					    MDIO_CHECK_SET_ST);
		if (ret)
			dev_err(&bus->dev, "MDIO en clk fail\n");
	} else if (is_acpi_node(bus->parent->fwnode)) {
		acpi_status s;

		s = acpi_evaluate_object(ACPI_HANDLE(bus->parent),
					 "_RST", NULL, NULL);
		if (ACPI_FAILURE(s)) {
			dev_err(&bus->dev, "Reset failed, return:%#x\n", s);
			ret = -EBUSY;
		} else {
			ret = 0;
		}
	} else {
		dev_err(&bus->dev, "Can not get cfg data from DT or ACPI\n");
		ret = -ENXIO;
	}
	return ret;
}