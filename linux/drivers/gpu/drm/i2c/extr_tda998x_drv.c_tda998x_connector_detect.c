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
typedef  int u8 ;
struct tda998x_priv {int dummy; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int CEC_RXSHPDLEV_HPD ; 
 int /*<<< orphan*/  REG_CEC_RXSHPDLEV ; 
 int cec_read (struct tda998x_priv*,int /*<<< orphan*/ ) ; 
 struct tda998x_priv* conn_to_tda998x_priv (struct drm_connector*) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 

__attribute__((used)) static enum drm_connector_status
tda998x_connector_detect(struct drm_connector *connector, bool force)
{
	struct tda998x_priv *priv = conn_to_tda998x_priv(connector);
	u8 val = cec_read(priv, REG_CEC_RXSHPDLEV);

	return (val & CEC_RXSHPDLEV_HPD) ? connector_status_connected :
			connector_status_disconnected;
}