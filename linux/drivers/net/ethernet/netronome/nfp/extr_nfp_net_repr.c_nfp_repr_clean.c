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
struct nfp_repr {int /*<<< orphan*/  port; scalar_t__ dst; int /*<<< orphan*/  netdev; int /*<<< orphan*/  app; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  nfp_app_repr_clean (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_port_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_repr_clean(struct nfp_repr *repr)
{
	unregister_netdev(repr->netdev);
	nfp_app_repr_clean(repr->app, repr->netdev);
	dst_release((struct dst_entry *)repr->dst);
	nfp_port_free(repr->port);
}