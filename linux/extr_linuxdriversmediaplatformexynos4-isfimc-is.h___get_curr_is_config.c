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
struct fimc_is {size_t config_index; struct chain_config* config; } ;
struct chain_config {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct chain_config *__get_curr_is_config(struct fimc_is *is)
{
	return &is->config[is->config_index];
}