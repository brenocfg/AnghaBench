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
struct TYPE_2__ {int ACK; scalar_t__ PHY_TEST_PATTERN; scalar_t__ LINK_TEST_PATTRN; scalar_t__ LINK_TRAINING; } ;
union test_response {int /*<<< orphan*/  raw; TYPE_1__ bits; } ;
union test_request {int /*<<< orphan*/  raw; TYPE_1__ bits; } ;
typedef  int /*<<< orphan*/  test_response ;
typedef  int /*<<< orphan*/  test_request ;
struct dc_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TEST_REQUEST ; 
 int /*<<< orphan*/  DP_TEST_RESPONSE ; 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  core_link_write_dpcd (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dp_test_send_link_test_pattern (struct dc_link*) ; 
 int /*<<< orphan*/  dp_test_send_link_training (struct dc_link*) ; 
 int /*<<< orphan*/  dp_test_send_phy_test_pattern (struct dc_link*) ; 
 int /*<<< orphan*/  memset (union test_response*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handle_automated_test(struct dc_link *link)
{
	union test_request test_request;
	union test_response test_response;

	memset(&test_request, 0, sizeof(test_request));
	memset(&test_response, 0, sizeof(test_response));

	core_link_read_dpcd(
		link,
		DP_TEST_REQUEST,
		&test_request.raw,
		sizeof(union test_request));
	if (test_request.bits.LINK_TRAINING) {
		/* ACK first to let DP RX test box monitor LT sequence */
		test_response.bits.ACK = 1;
		core_link_write_dpcd(
			link,
			DP_TEST_RESPONSE,
			&test_response.raw,
			sizeof(test_response));
		dp_test_send_link_training(link);
		/* no acknowledge request is needed again */
		test_response.bits.ACK = 0;
	}
	if (test_request.bits.LINK_TEST_PATTRN) {
		dp_test_send_link_test_pattern(link);
		test_response.bits.ACK = 1;
	}
	if (test_request.bits.PHY_TEST_PATTERN) {
		dp_test_send_phy_test_pattern(link);
		test_response.bits.ACK = 1;
	}

	/* send request acknowledgment */
	if (test_response.bits.ACK)
		core_link_write_dpcd(
			link,
			DP_TEST_RESPONSE,
			&test_response.raw,
			sizeof(test_response));
}