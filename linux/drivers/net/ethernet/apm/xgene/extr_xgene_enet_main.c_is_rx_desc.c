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
struct xgene_enet_raw_desc {int /*<<< orphan*/  m0; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPQNUM ; 
 scalar_t__ GET_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_rx_desc(struct xgene_enet_raw_desc *raw_desc)
{
	return GET_VAL(FPQNUM, le64_to_cpu(raw_desc->m0)) ? true : false;
}