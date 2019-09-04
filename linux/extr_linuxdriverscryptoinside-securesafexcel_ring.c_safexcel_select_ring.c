#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int rings; } ;
struct safexcel_crypto_priv {TYPE_1__ config; int /*<<< orphan*/  ring_used; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

inline int safexcel_select_ring(struct safexcel_crypto_priv *priv)
{
	return (atomic_inc_return(&priv->ring_used) % priv->config.rings);
}