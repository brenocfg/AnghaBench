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
struct nfp_app {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_tunnel_config_stop (struct nfp_app*) ; 

__attribute__((used)) static void nfp_flower_stop(struct nfp_app *app)
{
	nfp_tunnel_config_stop(app);
}