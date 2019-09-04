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
typedef  int u32 ;
struct scmi_msg_hdr {int /*<<< orphan*/  protocol_id; int /*<<< orphan*/  seq; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_ID_MASK ; 
 int /*<<< orphan*/  MSG_PROTOCOL_ID_MASK ; 
 int /*<<< orphan*/  MSG_TOKEN_ID_MASK ; 

__attribute__((used)) static inline u32 pack_scmi_header(struct scmi_msg_hdr *hdr)
{
	return FIELD_PREP(MSG_ID_MASK, hdr->id) |
		FIELD_PREP(MSG_TOKEN_ID_MASK, hdr->seq) |
		FIELD_PREP(MSG_PROTOCOL_ID_MASK, hdr->protocol_id);
}