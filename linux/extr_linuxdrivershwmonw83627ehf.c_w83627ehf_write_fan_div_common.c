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
struct w83627ehf_sio_data {scalar_t__ kind; } ;
struct w83627ehf_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct w83627ehf_sio_data* dev_get_platdata (struct device*) ; 
 scalar_t__ nct6775 ; 
 int /*<<< orphan*/  nct6775_write_fan_div (struct w83627ehf_data*,int) ; 
 scalar_t__ nct6776 ; 
 int /*<<< orphan*/  w83627ehf_write_fan_div (struct w83627ehf_data*,int) ; 

__attribute__((used)) static void w83627ehf_write_fan_div_common(struct device *dev,
					   struct w83627ehf_data *data, int nr)
{
	struct w83627ehf_sio_data *sio_data = dev_get_platdata(dev);

	if (sio_data->kind == nct6776)
		; /* no dividers, do nothing */
	else if (sio_data->kind == nct6775)
		nct6775_write_fan_div(data, nr);
	else
		w83627ehf_write_fan_div(data, nr);
}