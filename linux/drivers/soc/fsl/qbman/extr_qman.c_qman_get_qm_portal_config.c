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
struct qman_portal {struct qm_portal_config const* config; } ;
struct qm_portal_config {int dummy; } ;

/* Variables and functions */

const struct qm_portal_config *qman_get_qm_portal_config(
						struct qman_portal *portal)
{
	return portal->config;
}