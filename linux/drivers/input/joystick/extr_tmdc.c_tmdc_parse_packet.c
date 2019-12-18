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
struct tmdc_port {unsigned char mode; int absc; scalar_t__* abs; int* btnc; int* btno; int /*<<< orphan*/  dev; int /*<<< orphan*/ * btn; } ;
struct TYPE_2__ {unsigned char x; unsigned char y; } ;

/* Variables and functions */
 scalar_t__ ABS_HAT0X ; 
 scalar_t__ ABS_HAT0Y ; 
 size_t TMDC_BYTE_ID ; 
#define  TMDC_MODE_AT 129 
#define  TMDC_MODE_M3DI 128 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 size_t* tmdc_byte_a ; 
 size_t* tmdc_byte_d ; 
 TYPE_1__* tmdc_hat_to_axis ; 

__attribute__((used)) static int tmdc_parse_packet(struct tmdc_port *port, unsigned char *data)
{
	int i, k, l;

	if (data[TMDC_BYTE_ID] != port->mode)
		return -1;

	for (i = 0; i < port->absc; i++) {
		if (port->abs[i] < 0)
			return 0;

		input_report_abs(port->dev, port->abs[i], data[tmdc_byte_a[i]]);
	}

	switch (port->mode) {

		case TMDC_MODE_M3DI:

			i = tmdc_byte_d[0];
			input_report_abs(port->dev, ABS_HAT0X, ((data[i] >> 3) & 1) - ((data[i] >> 1) & 1));
			input_report_abs(port->dev, ABS_HAT0Y, ((data[i] >> 2) & 1) - ( data[i]       & 1));
			break;

		case TMDC_MODE_AT:

			i = tmdc_byte_a[3];
			input_report_abs(port->dev, ABS_HAT0X, tmdc_hat_to_axis[(data[i] - 141) / 25].x);
			input_report_abs(port->dev, ABS_HAT0Y, tmdc_hat_to_axis[(data[i] - 141) / 25].y);
			break;

	}

	for (k = l = 0; k < 4; k++) {
		for (i = 0; i < port->btnc[k]; i++)
			input_report_key(port->dev, port->btn[i + l],
				((data[tmdc_byte_d[k]] >> (i + port->btno[k])) & 1));
		l += port->btnc[k];
	}

	input_sync(port->dev);

	return 0;
}