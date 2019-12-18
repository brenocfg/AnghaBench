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
struct nfp_dump_tl {int /*<<< orphan*/  length; } ;
struct nfp_dump_error {int dummy; } ;

/* Variables and functions */
 int ALIGN8 (scalar_t__) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_dump_error_tlv_size(struct nfp_dump_tl *spec)
{
	return ALIGN8(sizeof(struct nfp_dump_error) + sizeof(*spec) +
		      be32_to_cpu(spec->length));
}