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
typedef  int u32 ;
struct sc27xx_adc_linear_graph {void* adc1; void* adc0; } ;
struct sc27xx_adc_data {int /*<<< orphan*/  dev; } ;
typedef  void nvmem_cell ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 struct sc27xx_adc_linear_graph big_scale_graph ; 
 struct sc27xx_adc_linear_graph big_scale_graph_calib ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,int) ; 
 void* nvmem_cell_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nvmem_cell_put (void*) ; 
 void* nvmem_cell_read (void*,size_t*) ; 
 void* sc27xx_adc_get_calib_data (int,void*) ; 
 struct sc27xx_adc_linear_graph small_scale_graph ; 
 struct sc27xx_adc_linear_graph small_scale_graph_calib ; 

__attribute__((used)) static int sc27xx_adc_scale_calibration(struct sc27xx_adc_data *data,
					bool big_scale)
{
	const struct sc27xx_adc_linear_graph *calib_graph;
	struct sc27xx_adc_linear_graph *graph;
	struct nvmem_cell *cell;
	const char *cell_name;
	u32 calib_data = 0;
	void *buf;
	size_t len;

	if (big_scale) {
		calib_graph = &big_scale_graph_calib;
		graph = &big_scale_graph;
		cell_name = "big_scale_calib";
	} else {
		calib_graph = &small_scale_graph_calib;
		graph = &small_scale_graph;
		cell_name = "small_scale_calib";
	}

	cell = nvmem_cell_get(data->dev, cell_name);
	if (IS_ERR(cell))
		return PTR_ERR(cell);

	buf = nvmem_cell_read(cell, &len);
	nvmem_cell_put(cell);

	if (IS_ERR(buf))
		return PTR_ERR(buf);

	memcpy(&calib_data, buf, min(len, sizeof(u32)));

	/* Only need to calibrate the adc values in the linear graph. */
	graph->adc0 = sc27xx_adc_get_calib_data(calib_data, calib_graph->adc0);
	graph->adc1 = sc27xx_adc_get_calib_data(calib_data >> 8,
						calib_graph->adc1);

	kfree(buf);
	return 0;
}