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
struct intel_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  HDCP_2_2_DELAY_BEFORE_ENCRYPTION_EN ; 
 int hdcp2_authenticate_sink (struct intel_connector*) ; 
 scalar_t__ hdcp2_deauthenticate_port (struct intel_connector*) ; 
 int hdcp2_enable_encryption (struct intel_connector*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdcp2_authenticate_and_encrypt(struct intel_connector *connector)
{
	int ret, i, tries = 3;

	for (i = 0; i < tries; i++) {
		ret = hdcp2_authenticate_sink(connector);
		if (!ret)
			break;

		/* Clearing the mei hdcp session */
		DRM_DEBUG_KMS("HDCP2.2 Auth %d of %d Failed.(%d)\n",
			      i + 1, tries, ret);
		if (hdcp2_deauthenticate_port(connector) < 0)
			DRM_DEBUG_KMS("Port deauth failed.\n");
	}

	if (i != tries) {
		/*
		 * Ensuring the required 200mSec min time interval between
		 * Session Key Exchange and encryption.
		 */
		msleep(HDCP_2_2_DELAY_BEFORE_ENCRYPTION_EN);
		ret = hdcp2_enable_encryption(connector);
		if (ret < 0) {
			DRM_DEBUG_KMS("Encryption Enable Failed.(%d)\n", ret);
			if (hdcp2_deauthenticate_port(connector) < 0)
				DRM_DEBUG_KMS("Port deauth failed.\n");
		}
	}

	return ret;
}