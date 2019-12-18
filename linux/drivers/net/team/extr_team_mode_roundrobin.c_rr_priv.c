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
struct team {int /*<<< orphan*/  mode_priv; } ;
struct rr_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct rr_priv *rr_priv(struct team *team)
{
	return (struct rr_priv *) &team->mode_priv;
}