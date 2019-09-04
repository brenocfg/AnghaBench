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
struct sharp_panel {struct mipi_dsi_device* link1; struct mipi_dsi_device* link2; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct mipi_dsi_device {int lanes; TYPE_1__ dev; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  format; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int /*<<< orphan*/  MIPI_DSI_MODE_LPM ; 
 struct sharp_panel* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct sharp_panel*) ; 
 struct mipi_dsi_device* of_find_mipi_dsi_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int sharp_panel_add (struct sharp_panel*) ; 
 int /*<<< orphan*/  sharp_panel_del (struct sharp_panel*) ; 

__attribute__((used)) static int sharp_panel_probe(struct mipi_dsi_device *dsi)
{
	struct mipi_dsi_device *secondary = NULL;
	struct sharp_panel *sharp;
	struct device_node *np;
	int err;

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_LPM;

	/* Find DSI-LINK1 */
	np = of_parse_phandle(dsi->dev.of_node, "link2", 0);
	if (np) {
		secondary = of_find_mipi_dsi_device_by_node(np);
		of_node_put(np);

		if (!secondary)
			return -EPROBE_DEFER;
	}

	/* register a panel for only the DSI-LINK1 interface */
	if (secondary) {
		sharp = devm_kzalloc(&dsi->dev, sizeof(*sharp), GFP_KERNEL);
		if (!sharp) {
			put_device(&secondary->dev);
			return -ENOMEM;
		}

		mipi_dsi_set_drvdata(dsi, sharp);

		sharp->link2 = secondary;
		sharp->link1 = dsi;

		err = sharp_panel_add(sharp);
		if (err < 0) {
			put_device(&secondary->dev);
			return err;
		}
	}

	err = mipi_dsi_attach(dsi);
	if (err < 0) {
		if (secondary)
			sharp_panel_del(sharp);

		return err;
	}

	return 0;
}