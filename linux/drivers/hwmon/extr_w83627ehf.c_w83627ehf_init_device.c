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
typedef  int u8 ;
struct w83627ehf_data {int have_temp; char** temp_label; size_t* temp_src; int* temp_type; int /*<<< orphan*/ * reg_temp_config; } ;
typedef  enum kinds { ____Placeholder_kinds } kinds ;

/* Variables and functions */
 int NUM_REG_TEMP ; 
 int /*<<< orphan*/  W83627EHF_REG_CONFIG ; 
 int /*<<< orphan*/  W83627EHF_REG_DIODE ; 
 int /*<<< orphan*/  W83627EHF_REG_VBAT ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
#define  w83627ehf 129 
 int w83627ehf_read_value (struct w83627ehf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627ehf_write_value (struct w83627ehf_data*,int /*<<< orphan*/ ,int) ; 
#define  w83627uhg 128 

__attribute__((used)) static inline void w83627ehf_init_device(struct w83627ehf_data *data,
						   enum kinds kind)
{
	int i;
	u8 tmp, diode;

	/* Start monitoring is needed */
	tmp = w83627ehf_read_value(data, W83627EHF_REG_CONFIG);
	if (!(tmp & 0x01))
		w83627ehf_write_value(data, W83627EHF_REG_CONFIG,
				      tmp | 0x01);

	/* Enable temperature sensors if needed */
	for (i = 0; i < NUM_REG_TEMP; i++) {
		if (!(data->have_temp & (1 << i)))
			continue;
		if (!data->reg_temp_config[i])
			continue;
		tmp = w83627ehf_read_value(data,
					   data->reg_temp_config[i]);
		if (tmp & 0x01)
			w83627ehf_write_value(data,
					      data->reg_temp_config[i],
					      tmp & 0xfe);
	}

	/* Enable VBAT monitoring if needed */
	tmp = w83627ehf_read_value(data, W83627EHF_REG_VBAT);
	if (!(tmp & 0x01))
		w83627ehf_write_value(data, W83627EHF_REG_VBAT, tmp | 0x01);

	/* Get thermal sensor types */
	switch (kind) {
	case w83627ehf:
		diode = w83627ehf_read_value(data, W83627EHF_REG_DIODE);
		break;
	case w83627uhg:
		diode = 0x00;
		break;
	default:
		diode = 0x70;
	}
	for (i = 0; i < 3; i++) {
		const char *label = NULL;

		if (data->temp_label)
			label = data->temp_label[data->temp_src[i]];

		/* Digital source overrides analog type */
		if (label && strncmp(label, "PECI", 4) == 0)
			data->temp_type[i] = 6;
		else if (label && strncmp(label, "AMD", 3) == 0)
			data->temp_type[i] = 5;
		else if ((tmp & (0x02 << i)))
			data->temp_type[i] = (diode & (0x10 << i)) ? 1 : 3;
		else
			data->temp_type[i] = 4; /* thermistor */
	}
}