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
struct mrvl_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  rawq; int /*<<< orphan*/  txq; } ;
struct hci_uart {struct mrvl_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STATE_CHIP_VER_PENDING ; 
 struct mrvl_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mrvl_open(struct hci_uart *hu)
{
	struct mrvl_data *mrvl;

	BT_DBG("hu %p", hu);

	mrvl = kzalloc(sizeof(*mrvl), GFP_KERNEL);
	if (!mrvl)
		return -ENOMEM;

	skb_queue_head_init(&mrvl->txq);
	skb_queue_head_init(&mrvl->rawq);

	set_bit(STATE_CHIP_VER_PENDING, &mrvl->flags);

	hu->priv = mrvl;
	return 0;
}