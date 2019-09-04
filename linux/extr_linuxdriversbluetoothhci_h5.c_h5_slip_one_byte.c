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
struct sk_buff {int dummy; } ;

/* Variables and functions */
#define  SLIP_DELIMITER 129 
#define  SLIP_ESC 128 
 char const SLIP_ESC_DELIM ; 
 char const SLIP_ESC_ESC ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,...) ; 

__attribute__((used)) static void h5_slip_one_byte(struct sk_buff *skb, u8 c)
{
	const char esc_delim[2] = { SLIP_ESC, SLIP_ESC_DELIM };
	const char esc_esc[2] = { SLIP_ESC, SLIP_ESC_ESC };

	switch (c) {
	case SLIP_DELIMITER:
		skb_put_data(skb, &esc_delim, 2);
		break;
	case SLIP_ESC:
		skb_put_data(skb, &esc_esc, 2);
		break;
	default:
		skb_put_data(skb, &c, 1);
	}
}