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
struct ssp_msg {int dummy; } ;
struct ssp_data {int dummy; } ;

/* Variables and functions */
 int ssp_do_transfer (struct ssp_data*,struct ssp_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ssp_spi_sync_command(struct ssp_data *data,
				       struct ssp_msg *msg)
{
	return ssp_do_transfer(data, msg, NULL, 0);
}