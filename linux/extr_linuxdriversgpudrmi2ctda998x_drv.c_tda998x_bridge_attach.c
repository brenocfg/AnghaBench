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
struct tda998x_priv {int dummy; } ;
struct drm_bridge {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct tda998x_priv* bridge_to_tda998x_priv (struct drm_bridge*) ; 
 int tda998x_connector_init (struct tda998x_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda998x_bridge_attach(struct drm_bridge *bridge)
{
	struct tda998x_priv *priv = bridge_to_tda998x_priv(bridge);

	return tda998x_connector_init(priv, bridge->dev);
}