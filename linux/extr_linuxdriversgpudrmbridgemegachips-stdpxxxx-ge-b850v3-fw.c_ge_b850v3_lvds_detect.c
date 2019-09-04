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
struct i2c_client {int dummy; } ;
struct drm_connector {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_2__ {struct i2c_client* stdp4028_i2c; } ;

/* Variables and functions */
 scalar_t__ STDP4028_CON_STATE_CONNECTED ; 
 int /*<<< orphan*/  STDP4028_DPTX_STS_REG ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 TYPE_1__* ge_b850v3_lvds_ptr ; 
 scalar_t__ i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_connector_status ge_b850v3_lvds_detect(
		struct drm_connector *connector, bool force)
{
	struct i2c_client *stdp4028_i2c =
			ge_b850v3_lvds_ptr->stdp4028_i2c;
	s32 link_state;

	link_state = i2c_smbus_read_word_data(stdp4028_i2c,
					      STDP4028_DPTX_STS_REG);

	if (link_state == STDP4028_CON_STATE_CONNECTED)
		return connector_status_connected;

	if (link_state == 0)
		return connector_status_disconnected;

	return connector_status_unknown;
}