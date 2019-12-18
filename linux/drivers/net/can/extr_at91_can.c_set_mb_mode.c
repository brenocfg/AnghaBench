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
struct at91_priv {int dummy; } ;
typedef  enum at91_mb_mode { ____Placeholder_at91_mb_mode } at91_mb_mode ;

/* Variables and functions */
 int /*<<< orphan*/  set_mb_mode_prio (struct at91_priv const*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_mb_mode(const struct at91_priv *priv, unsigned int mb,
		enum at91_mb_mode mode)
{
	set_mb_mode_prio(priv, mb, mode, 0);
}