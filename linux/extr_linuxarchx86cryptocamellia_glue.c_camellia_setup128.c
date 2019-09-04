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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CAMELLIA_F (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA1L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA1R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA2L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA2R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA3L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA3R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA4L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA4R ; 
 int /*<<< orphan*/  ROLDQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  camellia_setup_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_unaligned_be64 (unsigned char const*) ; 

__attribute__((used)) static void camellia_setup128(const unsigned char *key, u64 *subkey)
{
	u64 kl, kr, ww;
	u64 subRL[26];

	/**
	 *  k == kl || kr (|| is concatenation)
	 */
	kl = get_unaligned_be64(key);
	kr = get_unaligned_be64(key + 8);

	/* generate KL dependent subkeys */
	/* kw1 */
	subRL[0] = kl;
	/* kw2 */
	subRL[1] = kr;

	/* rotation left shift 15bit */
	ROLDQ(kl, kr, 15);

	/* k3 */
	subRL[4] = kl;
	/* k4 */
	subRL[5] = kr;

	/* rotation left shift 15+30bit */
	ROLDQ(kl, kr, 30);

	/* k7 */
	subRL[10] = kl;
	/* k8 */
	subRL[11] = kr;

	/* rotation left shift 15+30+15bit */
	ROLDQ(kl, kr, 15);

	/* k10 */
	subRL[13] = kr;
	/* rotation left shift 15+30+15+17 bit */
	ROLDQ(kl, kr, 17);

	/* kl3 */
	subRL[16] = kl;
	/* kl4 */
	subRL[17] = kr;

	/* rotation left shift 15+30+15+17+17 bit */
	ROLDQ(kl, kr, 17);

	/* k13 */
	subRL[18] = kl;
	/* k14 */
	subRL[19] = kr;

	/* rotation left shift 15+30+15+17+17+17 bit */
	ROLDQ(kl, kr, 17);

	/* k17 */
	subRL[22] = kl;
	/* k18 */
	subRL[23] = kr;

	/* generate KA */
	kl = subRL[0];
	kr = subRL[1];
	CAMELLIA_F(kl, CAMELLIA_SIGMA1L, CAMELLIA_SIGMA1R, ww);
	kr ^= ww;
	CAMELLIA_F(kr, CAMELLIA_SIGMA2L, CAMELLIA_SIGMA2R, kl);

	/* current status == (kll, klr, w0, w1) */
	CAMELLIA_F(kl, CAMELLIA_SIGMA3L, CAMELLIA_SIGMA3R, kr);
	kr ^= ww;
	CAMELLIA_F(kr, CAMELLIA_SIGMA4L, CAMELLIA_SIGMA4R, ww);
	kl ^= ww;

	/* generate KA dependent subkeys */
	/* k1, k2 */
	subRL[2] = kl;
	subRL[3] = kr;
	ROLDQ(kl, kr, 15);
	/* k5,k6 */
	subRL[6] = kl;
	subRL[7] = kr;
	ROLDQ(kl, kr, 15);
	/* kl1, kl2 */
	subRL[8] = kl;
	subRL[9] = kr;
	ROLDQ(kl, kr, 15);
	/* k9 */
	subRL[12] = kl;
	ROLDQ(kl, kr, 15);
	/* k11, k12 */
	subRL[14] = kl;
	subRL[15] = kr;
	ROLDQ(kl, kr, 34);
	/* k15, k16 */
	subRL[20] = kl;
	subRL[21] = kr;
	ROLDQ(kl, kr, 17);
	/* kw3, kw4 */
	subRL[24] = kl;
	subRL[25] = kr;

	camellia_setup_tail(subkey, subRL, 24);
}