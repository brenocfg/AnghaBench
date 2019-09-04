#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {scalar_t__ bridge; struct hdcs* sensor_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct hdcs {int psmp; TYPE_1__ array; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int BIT (int) ; 
 scalar_t__ BRIDGE_STV602 ; 
 int HDCS_ADC_START_SIG_DUR ; 
 int HDCS_REG_CONFIG (struct sd*) ; 
 int HDCS_TCTRL ; 
 scalar_t__ IS_1020 (struct sd*) ; 
 int STV_STV0600_EMULATION ; 
 int /*<<< orphan*/  hdcs_reset (struct sd*) ; 
 int hdcs_set_size (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stv06xx_write_bridge (struct sd*,int,int) ; 
 int stv06xx_write_sensor (struct sd*,int,int) ; 
 int** stv_bridge_init ; 
 int** stv_sensor_init ; 

__attribute__((used)) static int hdcs_init(struct sd *sd)
{
	struct hdcs *hdcs = sd->sensor_priv;
	int i, err = 0;

	/* Set the STV0602AA in STV0600 emulation mode */
	if (sd->bridge == BRIDGE_STV602)
		stv06xx_write_bridge(sd, STV_STV0600_EMULATION, 1);

	/* Execute the bridge init */
	for (i = 0; i < ARRAY_SIZE(stv_bridge_init) && !err; i++) {
		err = stv06xx_write_bridge(sd, stv_bridge_init[i][0],
					   stv_bridge_init[i][1]);
	}
	if (err < 0)
		return err;

	/* sensor soft reset */
	hdcs_reset(sd);

	/* Execute the sensor init */
	for (i = 0; i < ARRAY_SIZE(stv_sensor_init) && !err; i++) {
		err = stv06xx_write_sensor(sd, stv_sensor_init[i][0],
					     stv_sensor_init[i][1]);
	}
	if (err < 0)
		return err;

	/* Enable continuous frame capture, bit 2: stop when frame complete */
	err = stv06xx_write_sensor(sd, HDCS_REG_CONFIG(sd), BIT(3));
	if (err < 0)
		return err;

	/* Set PGA sample duration
	(was 0x7E for the STV602, but caused slow framerate with HDCS-1020) */
	if (IS_1020(sd))
		err = stv06xx_write_sensor(sd, HDCS_TCTRL,
				(HDCS_ADC_START_SIG_DUR << 6) | hdcs->psmp);
	else
		err = stv06xx_write_sensor(sd, HDCS_TCTRL,
				(HDCS_ADC_START_SIG_DUR << 5) | hdcs->psmp);
	if (err < 0)
		return err;

	return hdcs_set_size(sd, hdcs->array.width, hdcs->array.height);
}