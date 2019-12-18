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
struct TYPE_2__ {int /*<<< orphan*/  recv; } ;
struct rx_desc {TYPE_1__ header; } ;

/* Variables and functions */
 int RXHDR_NEXT_RECV_FLAG ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ec_bhf_pkt_received(struct rx_desc *desc)
{
	return le32_to_cpu(desc->header.recv) & RXHDR_NEXT_RECV_FLAG;
}