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
typedef  int /*<<< orphan*/  u8 ;
struct intel_digital_port {int dummy; } ;
struct hdcp2_dp_errata_stream_type {int /*<<< orphan*/  stream_type; int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  stream_type_msg ;

/* Variables and functions */
 int /*<<< orphan*/  HDCP_2_2_ERRATA_DP_STREAM_TYPE ; 
 int intel_dp_hdcp2_write_msg (struct intel_digital_port*,struct hdcp2_dp_errata_stream_type*,int) ; 

__attribute__((used)) static
int intel_dp_hdcp2_config_stream_type(struct intel_digital_port *intel_dig_port,
				      bool is_repeater, u8 content_type)
{
	struct hdcp2_dp_errata_stream_type stream_type_msg;

	if (is_repeater)
		return 0;

	/*
	 * Errata for DP: As Stream type is used for encryption, Receiver
	 * should be communicated with stream type for the decryption of the
	 * content.
	 * Repeater will be communicated with stream type as a part of it's
	 * auth later in time.
	 */
	stream_type_msg.msg_id = HDCP_2_2_ERRATA_DP_STREAM_TYPE;
	stream_type_msg.stream_type = content_type;

	return intel_dp_hdcp2_write_msg(intel_dig_port, &stream_type_msg,
					sizeof(stream_type_msg));
}