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
typedef  int /*<<< orphan*/  u32 ;
struct nb8800_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nb8800_maskl (struct nb8800_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nb8800_modl(struct nb8800_priv *priv, int reg, u32 bits,
			       bool set)
{
	nb8800_maskl(priv, reg, bits, set ? bits : 0);
}