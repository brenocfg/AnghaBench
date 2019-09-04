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
struct MT2063_AvoidSpursData_t {int f_LO1; int f_LO2; int f_out; int f_out_bw; int f_zif_bw; int maxH1; } ;
typedef  int s32 ;

/* Variables and functions */
 int DIV_ROUND_UP (int const,int const) ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int gcd (int const,int const) ; 
 int max (int,int const) ; 

__attribute__((used)) static u32 IsSpurInBand(struct MT2063_AvoidSpursData_t *pAS_Info,
			u32 *fm, u32 * fp)
{
	/*
	 **  Calculate LO frequency settings.
	 */
	u32 n, n0;
	const u32 f_LO1 = pAS_Info->f_LO1;
	const u32 f_LO2 = pAS_Info->f_LO2;
	const u32 d = pAS_Info->f_out + pAS_Info->f_out_bw / 2;
	const u32 c = d - pAS_Info->f_out_bw;
	const u32 f = pAS_Info->f_zif_bw / 2;
	const u32 f_Scale = (f_LO1 / (UINT_MAX / 2 / pAS_Info->maxH1)) + 1;
	s32 f_nsLO1, f_nsLO2;
	s32 f_Spur;
	u32 ma, mb, mc, md, me, mf;
	u32 lo_gcd, gd_Scale, gc_Scale, gf_Scale, hgds, hgfs, hgcs;

	dprintk(2, "\n");

	*fm = 0;

	/*
	 ** For each edge (d, c & f), calculate a scale, based on the gcd
	 ** of f_LO1, f_LO2 and the edge value.  Use the larger of this
	 ** gcd-based scale factor or f_Scale.
	 */
	lo_gcd = gcd(f_LO1, f_LO2);
	gd_Scale = max((u32) gcd(lo_gcd, d), f_Scale);
	hgds = gd_Scale / 2;
	gc_Scale = max((u32) gcd(lo_gcd, c), f_Scale);
	hgcs = gc_Scale / 2;
	gf_Scale = max((u32) gcd(lo_gcd, f), f_Scale);
	hgfs = gf_Scale / 2;

	n0 = DIV_ROUND_UP(f_LO2 - d, f_LO1 - f_LO2);

	/*  Check out all multiples of LO1 from n0 to m_maxLOSpurHarmonic  */
	for (n = n0; n <= pAS_Info->maxH1; ++n) {
		md = (n * ((f_LO1 + hgds) / gd_Scale) -
		      ((d + hgds) / gd_Scale)) / ((f_LO2 + hgds) / gd_Scale);

		/*  If # fLO2 harmonics > m_maxLOSpurHarmonic, then no spurs present  */
		if (md >= pAS_Info->maxH1)
			break;

		ma = (n * ((f_LO1 + hgds) / gd_Scale) +
		      ((d + hgds) / gd_Scale)) / ((f_LO2 + hgds) / gd_Scale);

		/*  If no spurs between +/- (f_out + f_IFBW/2), then try next harmonic  */
		if (md == ma)
			continue;

		mc = (n * ((f_LO1 + hgcs) / gc_Scale) -
		      ((c + hgcs) / gc_Scale)) / ((f_LO2 + hgcs) / gc_Scale);
		if (mc != md) {
			f_nsLO1 = (s32) (n * (f_LO1 / gc_Scale));
			f_nsLO2 = (s32) (mc * (f_LO2 / gc_Scale));
			f_Spur =
			    (gc_Scale * (f_nsLO1 - f_nsLO2)) +
			    n * (f_LO1 % gc_Scale) - mc * (f_LO2 % gc_Scale);

			*fp = ((f_Spur - (s32) c) / (mc - n)) + 1;
			*fm = (((s32) d - f_Spur) / (mc - n)) + 1;
			return 1;
		}

		/*  Location of Zero-IF-spur to be checked  */
		me = (n * ((f_LO1 + hgfs) / gf_Scale) +
		      ((f + hgfs) / gf_Scale)) / ((f_LO2 + hgfs) / gf_Scale);
		mf = (n * ((f_LO1 + hgfs) / gf_Scale) -
		      ((f + hgfs) / gf_Scale)) / ((f_LO2 + hgfs) / gf_Scale);
		if (me != mf) {
			f_nsLO1 = n * (f_LO1 / gf_Scale);
			f_nsLO2 = me * (f_LO2 / gf_Scale);
			f_Spur =
			    (gf_Scale * (f_nsLO1 - f_nsLO2)) +
			    n * (f_LO1 % gf_Scale) - me * (f_LO2 % gf_Scale);

			*fp = ((f_Spur + (s32) f) / (me - n)) + 1;
			*fm = (((s32) f - f_Spur) / (me - n)) + 1;
			return 1;
		}

		mb = (n * ((f_LO1 + hgcs) / gc_Scale) +
		      ((c + hgcs) / gc_Scale)) / ((f_LO2 + hgcs) / gc_Scale);
		if (ma != mb) {
			f_nsLO1 = n * (f_LO1 / gc_Scale);
			f_nsLO2 = ma * (f_LO2 / gc_Scale);
			f_Spur =
			    (gc_Scale * (f_nsLO1 - f_nsLO2)) +
			    n * (f_LO1 % gc_Scale) - ma * (f_LO2 % gc_Scale);

			*fp = (((s32) d + f_Spur) / (ma - n)) + 1;
			*fm = (-(f_Spur + (s32) c) / (ma - n)) + 1;
			return 1;
		}
	}

	/*  No spurs found  */
	return 0;
}