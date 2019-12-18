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
struct bman_portal {struct bm_portal_config const* config; } ;
struct bm_portal_config {int dummy; } ;

/* Variables and functions */

const struct bm_portal_config *
bman_get_bm_portal_config(const struct bman_portal *portal)
{
	return portal->config;
}