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
struct qeth_ipa_cmd {int dummy; } ;
struct qeth_cmd_buffer {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ IPA_PDU_HEADER_SIZE ; 

__attribute__((used)) static inline struct qeth_ipa_cmd *__ipa_cmd(struct qeth_cmd_buffer *iob)
{
	return (struct qeth_ipa_cmd *)(iob->data + IPA_PDU_HEADER_SIZE);
}