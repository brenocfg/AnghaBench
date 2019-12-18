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

/* Variables and functions */
 int /*<<< orphan*/  WDRTAS_SP_SPI ; 
 int WDRTAS_SP_SPI_LEN ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,long) ; 
 long rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtas_data_buf ; 
 int /*<<< orphan*/  rtas_data_buf_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdrtas_token_get_sp ; 

__attribute__((used)) static int wdrtas_get_interval(int fallback_value)
{
	long result;
	char value[WDRTAS_SP_SPI_LEN];

	spin_lock(&rtas_data_buf_lock);
	memset(rtas_data_buf, 0, WDRTAS_SP_SPI_LEN);
	result = rtas_call(wdrtas_token_get_sp, 3, 1, NULL,
			   WDRTAS_SP_SPI, __pa(rtas_data_buf),
			   WDRTAS_SP_SPI_LEN);

	memcpy(value, rtas_data_buf, WDRTAS_SP_SPI_LEN);
	spin_unlock(&rtas_data_buf_lock);

	if (value[0] != 0 || value[1] != 2 || value[3] != 0 || result < 0) {
		pr_warn("could not get sp_spi watchdog timeout (%li). Continuing\n",
			result);
		return fallback_value;
	}

	/* rtas uses minutes */
	return ((int)value[2]) * 60;
}