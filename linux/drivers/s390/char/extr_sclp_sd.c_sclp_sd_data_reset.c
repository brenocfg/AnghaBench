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
struct sclp_sd_data {scalar_t__ esize_bytes; scalar_t__ dsize_bytes; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sclp_sd_data_reset(struct sclp_sd_data *data)
{
	vfree(data->data);
	data->data = NULL;
	data->dsize_bytes = 0;
	data->esize_bytes = 0;
}