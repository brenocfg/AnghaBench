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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MLX5_FIELD_SUPPORT_MPLS_EXP ; 
 int MLX5_FIELD_SUPPORT_MPLS_LABEL ; 
 int MLX5_FIELD_SUPPORT_MPLS_S_BOS ; 
 int MLX5_FIELD_SUPPORT_MPLS_TTL ; 
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fte_match_mpls ; 
 int /*<<< orphan*/  mpls_exp ; 
 int /*<<< orphan*/  mpls_label ; 
 int /*<<< orphan*/  mpls_s_bos ; 
 int /*<<< orphan*/  mpls_ttl ; 

__attribute__((used)) static int check_mpls_supp_fields(u32 field_support, const __be32 *set_mask)
{
	if (MLX5_GET(fte_match_mpls, set_mask, mpls_label) &&
	    !(field_support & MLX5_FIELD_SUPPORT_MPLS_LABEL))
		return -EOPNOTSUPP;

	if (MLX5_GET(fte_match_mpls, set_mask, mpls_exp) &&
	    !(field_support & MLX5_FIELD_SUPPORT_MPLS_EXP))
		return -EOPNOTSUPP;

	if (MLX5_GET(fte_match_mpls, set_mask, mpls_s_bos) &&
	    !(field_support & MLX5_FIELD_SUPPORT_MPLS_S_BOS))
		return -EOPNOTSUPP;

	if (MLX5_GET(fte_match_mpls, set_mask, mpls_ttl) &&
	    !(field_support & MLX5_FIELD_SUPPORT_MPLS_TTL))
		return -EOPNOTSUPP;

	return 0;
}