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
struct request_context {int dummy; } ;
struct hermes {struct ezusb_priv* priv; } ;
struct ezusb_priv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EZUSB_FRAME_CONTROL ; 
 int /*<<< orphan*/  EZUSB_RID_ACK ; 
 int /*<<< orphan*/  EZUSB_RID_PROG_END ; 
 int ezusb_access_ltv (struct ezusb_priv*,struct request_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct request_context* ezusb_alloc_ctx (struct ezusb_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ezusb_program_end(struct hermes *hw)
{
	struct ezusb_priv *upriv = hw->priv;
	struct request_context *ctx;

	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_PROG_END, EZUSB_RID_ACK);
	if (!ctx)
		return -ENOMEM;

	return ezusb_access_ltv(upriv, ctx, 0, NULL,
				EZUSB_FRAME_CONTROL, NULL, 0, NULL);
}