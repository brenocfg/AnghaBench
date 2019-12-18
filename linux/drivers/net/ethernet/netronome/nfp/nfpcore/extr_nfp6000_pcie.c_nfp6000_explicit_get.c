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
struct nfp_cpp_explicit {int dummy; } ;
struct nfp6000_explicit_priv {scalar_t__ data; } ;

/* Variables and functions */
 struct nfp6000_explicit_priv* nfp_cpp_explicit_priv (struct nfp_cpp_explicit*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int nfp6000_explicit_get(struct nfp_cpp_explicit *expl,
				void *buff, size_t len)
{
	struct nfp6000_explicit_priv *priv = nfp_cpp_explicit_priv(expl);
	u32 *dst = buff;
	size_t i;

	for (i = 0; i < len; i += sizeof(u32))
		*(dst++) = readl(priv->data + i);

	return i;
}